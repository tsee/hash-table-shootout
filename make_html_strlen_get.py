import sys
html_template = file('charts-template-strlen_get.html', 'r').read()
file('charts_strlen_get.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', sys.stdin.read()))
