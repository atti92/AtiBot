import re
from willie import web
from willie.module import command, commands, example
import string
import HTMLParser

@commands('getshieldstats', 'getshieldinfo')
@example('.getshieldstats Vazaha Haven 7')
def getshieldstats(bot, trigger):
	"""Star Sonata WIKI."""
	result = ''
	name = trigger.group(2)
	name = re.escape(name)
	q = web.get('http://wiki2.starsonata.com/index.php/Shields')
	if(re.search(name, q)):
		mstring = '<tr>.?<td>.?'+name + '[\ \n\r]</td>'
		for x in xrange(1,15):
			mstring += '.*?<td.*?>(.*?)</td>'
			pass
		m = re.search( mstring, q, re.MULTILINE|re.DOTALL|re.I)
		m2string = '(?!<tr>.?<td>.?Name.*?</table>.*?' +name+ ')<tr>.?<td>.?Name[\ \n\r]*?</td>'
		for x in xrange(1,15):
			m2string += '.*?<td.*?>(.*?)</td>'
			pass
		m2string += '.*?' + name
		m2 = re.search(m2string, q, re.MULTILINE|re.DOTALL|re.I)
		statname = ['Name']
		for x in xrange(1,15):
			statname.append(m2.group(x))
			pass
		result = statname[0] + ': ' + trigger.group(2) + ' '
		for x in xrange(1,15):
			result += statname[x] + ': '
			result += m.group(x) + ' '
			pass
	else:
		result = 'No result!'
	bot.reply(result)
getshieldstats.priority = 'low'