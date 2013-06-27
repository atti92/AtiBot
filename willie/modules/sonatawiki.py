import re
from willie import web
from willie.module import command, commands, example
import string
import platform
import socket
import time
import sys
import subprocess
import HTMLParser

socket.setdefaulttimeout(10)
INTERVAL = 30
host = [
		{'host': 'liberty.starsonata.com', 'name':'Liberty', 'port':3030, 'ch':True},
		{'host': 'test.starsonata.com', 'name':'LiveTest', 'port':3030, 'ch':True},
		{'host': 'test.starsonata.com', 'name':'Test', 'port':3032, 'ch':True}
		
	]

@commands('updateandrestart')
@example('.updateandrestart')
def updateandrestart(bot, trigger):
    """
    Manage atibot update through github and restart process
    """
    if not trigger.admin:
        return
    subprocess.Popen("../updateatibot.sh", shell=True)

def check_server(address, port):
	# Create a TCP socket
	s = socket.socket()
	#print "Attempting to connect to %s on port %s" % (address, port)
	try:
		s.connect((address, port))
		#print "Connected to %s on port %s" % (address, port)
		s.close()
		return True
	except socket.error, e:
		print "Connection to %s on port %s failed: %s" % (address, port, e)
		return False

def ping(host):
	result = 1
	if platform.system() is 'Linux':
		result = subprocess.call(["ping","-c","1",host],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	elif platform.system() is 'Windows':
		result = subprocess.call(["ping",host],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	if result is 0:
		return True
	elif result is 1:
		raise Exception('Host not found')
	elif result is 2:
		raise Exception('Ping timed out')
	return result

def gettablecontent(q, num, item):
	"""Getting table data"""
	result = ''
	if(re.search(re.escape(item), q, re.MULTILINE|re.IGNORECASE)):
		mstring = '<tr.*?>.?<td.*?>.?'+ re.escape(item) + '[\ \n\r]</td>'
		for x in xrange(1,num+1):
			mstring += '.*?<td.*?>(.*?)</td>'
			pass
		m = re.search( mstring, q, re.MULTILINE|re.DOTALL|re.IGNORECASE)
		if m is None:
			return 'Can\'t find item'
		m2string = '(?!<tr>.?<td.*?>.?(?:<b>)?.?Name.*?</table>.*?' +re.escape(item)+ ')<tr>.?<td.*?>.?(?:<b>)?.?Name.*?</td>'

		for x in xrange(1,num+1):
			m2string += '.*?<td.*?>.?(?:<b>)?(.*?)(?:</b>)?</td>'
			pass
		m2string += '.*?' + re.escape(item)
		m2 = re.search(m2string, q, re.MULTILINE|re.DOTALL|re.IGNORECASE)
		if m2 is None:
			return 'Can\'t find header'
		statname = ['Name']
		for x in xrange(1,num+1):
			statname.append(m2.group(x))
			pass
		result = statname[0] + ': ' + item + ' '
		for x in xrange(1,num+1):
			result += statname[x] + ': '
			result += m.group(x) + ' '
			pass
		result = re.sub(r'<a.*?>(.*?)</a>', r'\1', result)
		result = re.sub(r'\&\#160', r'-', result)
		result = re.sub(r'<.*?>', r'', result)
		pass
	else:
		result = 'Item not found!'
	return result

@commands('status')
@example('.status [servername]')
def serverstatus(bot, trigger):
	"""Get info about starsonata servers"""
	global host
	servname = 'liberty'
	if trigger.group(2) is not None:
		servname = trigger.group(2)

	for x in host:
		if re.search(x['name'], servname, re.IGNORECASE) is not None:
			reply = x['name'] + " (" + x['host'] + ":" + str(x['port']) + ") is ";
			if check_server(x['host'], x['port']) is True:
				bot.reply(reply + "running.")
			else:
				bot.reply(reply + "down.")
		pass


@commands('getshieldstats', 'getshieldinfo')
@example('.getshieldstats Vazaha Haven 7')
def getshieldstats(bot, trigger):
	"""Star Sonata WIKI."""
	result = ''
	name = trigger.group(2)
	q = web.get('http://wiki2.starsonata.com/index.php/Shields')
	result = gettablecontent(q, 14, name)
	bot.reply(result)
getshieldstats.priority = 'low'

@commands('getenergystats', 'getenergyinfo')
@example('.getenergystats Dark Cage')
def getenergystats(bot, trigger):
	"""Star Sonata WIKI."""
	result = ''
	name = trigger.group(2)
	q = web.get('http://wiki2.starsonata.com/index.php/Energy')
	result = gettablecontent(q, 11, name)
	bot.reply(result)
getshieldstats.priority = 'low'

@commands('startservcheck')
@example('.startservcheck')
def startservcheck(bot, trigger):
	""" Begin checking serverstatus """
	if not trigger.admin:
		bot.reply("You must be an admin to start up the Server checks.")
		return
	global host
	global INTERVAL
	print 'Server checking began...'
	while True:
		for x in host:
			if check_server(x['host'], x['port']) is False:
				if x['ch'] is False:
					bot.msg(bot.nick, '.announce ' + x['name'] + ' (' + x['host'] + ':' + str(x['port']) + ') is down!')
					x['ch'] = True
			else:
				if x['ch'] is False:
					bot.msg(bot.nick, '.announce ' + x['name'] + ' (' + x['host'] + ':' + str(x['port']) + ') is up!')
					x['ch'] = True
			pass
		time.sleep(INTERVAL)