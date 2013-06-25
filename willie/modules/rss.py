# -*- coding: utf-8 -*-
"""
rss.py - Willie RSS Module
Copyright 2012, Michael Yanovich, yanovich.net
Licensed under the Eiffel Forum License 2.

http://willie.dfbta.net
"""

import feedparser
import socket
import sys
import time
import re

DEBUG = False
socket.setdefaulttimeout(10)
INTERVAL = 10  # seconds between checking for new updates
STOP = False
#This is reset in setup().
SUB = ('%s',)


def checkdb(cursor):
    cursor.execute("CREATE TABLE IF NOT EXISTS rss ( channel text, site_name text, site_url text, fg text, bg text)")

def setup(willie):
    global SUB
    SUB = (willie.db.substitution,)

def manage_rss(willie, trigger):
    """ .rss operation channel site_name url -- operation can be either 'add', 'del', or 'list' no further operators needed if 'list' used """
    if not trigger.admin:
        willie.reply("Sorry, you need to be an admin to modify the RSS feeds.")
        return
    conn = willie.db.connect()
    c = conn.cursor()
    checkdb(c)
    conn.commit()

    text = trigger.group().split()
    if len(text) < 2:
        willie.reply("Proper usage: '.rss add ##channel Site_Name URL', '.rss del ##channel Site_Name URL', '.rss del ##channel'")
    elif len(text) > 2:
        channel = text[2].lower()

    if len(text) > 4 and text[1] == 'add':
        fg_colour = str()
        bg_colour = str()
        temp = trigger.group().split('"')
        if len(temp) == 1:
            site_name = text[3]
            site_url = text[4]
            if len(text) >= 6:
                # .rss add ##yano ScienceDaily http://sciencedaily.com/ 03
                fg_colour = str(text[5])
            if len(text) == 7:
                # .rss add ##yano ScienceDaily http://sciencedaily.com/ 03 00
                bg_colour = str(text[6])
        elif temp[-1].split():
            site_name = temp[1]
            ending = temp[-1].split()
            site_url = ending[0]
            if len(ending) >= 2:
                fg_colour = ending[1]
            if len(ending) == 3:
                bg_colour = ending[2]
        else:
            willie.reply("Not enough parameters specified.")
            return
        if fg_colour:
            fg_colour = fg_colour.zfill(2)
        if bg_colour:
            bg_colour = bg_colour.zfill(2)
        c.execute('INSERT INTO rss VALUES (%s,%s,%s,%s,%s)' % (SUB*5), (channel, site_name, site_url, fg_colour, bg_colour))
        conn.commit()
        c.close()
        willie.reply("Successfully added values to database.")
    elif len(text) == 3 and text[1] == 'del':
        # .rss del ##channel
        c.execute('DELETE FROM rss WHERE channel = %s' % SUB, (channel,))
        conn.commit()
        c.close()
        willie.reply("Successfully removed values from database.")
    elif len(text) >= 4 and text[1] == 'del':
        # .rss del ##channel Site_Name
        c.execute('DELETE FROM rss WHERE channel = %s and site_name = %s' % (SUB*2), (channel, " ".join(text[3:])))
        conn.commit()
        c.close()
        willie.reply("Successfully removed the site from the given channel.")
    elif len(text) == 2 and text[1] == 'list':
        c.execute("SELECT * FROM rss")
        k = 0
        for row in c.fetchall():
            k += 1
            willie.say("list: " + unicode(row))
        if k == 0:
            willie.reply("No entries in database")
    else:
        willie.reply("Incorrect parameters specified.")
    conn.close()
manage_rss.commands = ['rss']
manage_rss.priority = 'low'


class Feed(object):
    modified = ''

first_run = True
restarted = False
feeds = dict()


def read_feeds(willie):
    global restarted
    global STOP

    restarted = False
    conn = willie.db.connect()
    cur = conn.cursor()
    checkdb(cur)
    cur.execute("SELECT * FROM rss")
    if not cur.fetchall():
        STOP = True
        willie.say("No RSS feeds found in database. Please add some rss feeds.")

    cur.execute("CREATE TABLE IF NOT EXISTS recent ( channel text, site_name text, article_title text, article_url text )")
    cur.execute("SELECT * FROM rss")

    for row in cur.fetchall():
        feed_channel = row[0]
        feed_site_name = row[1]
        feed_url = row[2]
        feed_fg = row[3]
        feed_bg = row[4]
        try:
            fp = feedparser.parse(feed_url)
        except IOError, E:
            willie.say("Can't parse, " + str(E))

        if fp is None:
            conn.close()
            return
        if not hasattr(fp, 'entries'):
            conn.close()
            return
        if fp.entries is None:
            conn.close()
            return
        entry = fp.entries[0]

        if not feed_fg and not feed_bg:
            site_name_effect = "[\x02%s\x02]" % (feed_site_name)
        elif feed_fg and not feed_bg:
            site_name_effect = "[\x02\x03%s%s\x03\x02]" % (feed_fg, feed_site_name)
        elif feed_fg and feed_bg:
            site_name_effect = "[\x02\x03%s,%s%s\x03\x02]" % (feed_fg, feed_bg, feed_site_name)
        showurl = False
        article_url = ''
        if hasattr(entry, 'author'):
            article_title = "<<" + entry.author + ">>:  "
        if hasattr(entry, 'id'):
            article_url = entry.id
            if re.search(r'Commit/', entry.id) is not None:
                article_url = re.sub(r'.*?Commit/(.*?)', 'Hash: \1', entry.id)
            elif re.search(r'https://.*/.*?', entry.id) is not None:
                article_url = re.sub(r'https://.*/(.*?)', 'Hash: \1', entry.id)
            showurl = True
        elif hasattr(entry, 'feedburner_origlink'):
            article_url = entry.feedburner_origlink
        else:
            article_url = entry.links[0].href
        if hasattr(entry, 'content'):
            m = re.search(r'<pre.*?>(.*?)</pre>', entry.content[0].value, re.DOTALL)
            content_text =  m.group(1).replace('\n','   ')
        else:
            content_text = entry.title
        #if hasattr(entry, 'title'):
        #    article_title += entry.title
        # only print if new entry
        sql_text = (feed_channel, feed_site_name, entry.title, article_url)
        cur.execute('SELECT * FROM recent WHERE channel = %s AND site_name = %s and article_title = %s AND article_url = %s' % (SUB*4), sql_text)
        if len(cur.fetchall()) < 1:
            if showurl is True:
                response = site_name_effect + " %s \x02%s\x02" % (article_title, article_url) 
            else:
                response = site_name_effect + " %s" % (article_title) 
            if entry.updated:
                response += " - %s" % (entry.updated)

            willie.msg(feed_channel, response)
            willie.msg(feed_channel, site_name_effect + " %s" % (content_text))

            t = (feed_channel, feed_site_name, entry.title, article_url,)
            cur.execute('INSERT INTO recent VALUES (%s, %s, %s, %s)' % (SUB*4), t)
            conn.commit()
        else:
            if DEBUG:
                willie.msg(feed_channel, u"Skipping previously read entry: %s %s" % (site_name_effect, entry.title))
    conn.close()


def startrss(willie, trigger):
    """ Begin reading RSS feeds """
    if not trigger.admin:
        willie.reply("You must be an admin to start up the RSS feeds.")
        return
    print 'Reading rss feeds...'
    global first_run, restarted, DEBUG, INTERVAL, STOP
    DEBUG = False

    query = trigger.group(2)
    if query == '-v':
        DEBUG = True
        STOP = False
        willie.reply("Debugging enabled.")
    elif query == '-q':
        DEBUG = False
        STOP = False
        willie.reply("Debugging disabled.")
    elif query == '-i':
        INTERVAL = trigger.group(3)
        willie.reply("INTERVAL updated to: %s" % (str(INTERVAL)))
    elif query == '--stop':
        STOP = True
        willie.reply("Stop parameter updated.")

    if first_run:
        if DEBUG:
            willie.say("Okay, I'll start rss fetching...")
        first_run = False
    else:
        restarted = True
        if DEBUG:
            willie.say("Okay, I'll re-start rss...")

    if not STOP:
        while True:
            if STOP:
                willie.reply("STOPPED")
                first_run = False
                STOP = False
                break
            if DEBUG:
                willie.say("Rechecking feeds")
            read_feeds(willie)
            time.sleep(INTERVAL)

    if DEBUG:
        willie.say("Stopped checking")
startrss.commands = ['startrss']
startrss.priority = 'high'

if __name__ == '__main__':
    print __doc__.strip()
