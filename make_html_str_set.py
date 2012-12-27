import sys
html_template = file('charts-template-str_set.html', 'r').read()
file('charts_str_set.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', sys.stdin.read()))
