import re
from willie import web
from willie.module import command, commands, example
import string
import HTMLParser

def gettablecontent(q, num, item):
	"""Getting table data"""
	result = ''
	if(re.search(item,q)):
		mstring = '<tr>.?<td>.?'+ re.escape(item) + '[\ \n\r]</td>'
		for x in xrange(1,num+1):
			mstring += '.*?<td.*?>(.*?)</td>'
			pass
		m = re.search( mstring, q, re.MULTILINE|re.DOTALL|re.IGNORECASE)
		m2string = '(?!<tr>.?<td>.?Name.*?</table>.*?' +re.escape(item)+ ')<tr>.?<td>.?Name[\ \n\r]*?</td>'
		for x in xrange(1,num+1):
			m2string += '.*?<td.*?>(.*?)</td>'
			pass
		m2string += '.*?' + re.escape(item)
		m2 = re.search(m2string, q, re.MULTILINE|re.DOTALL|re.IGNORECASE)
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