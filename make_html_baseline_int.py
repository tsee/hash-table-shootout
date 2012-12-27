import sys
html_template = file('charts-template-baseline_int.html', 'r').read()
file('charts_baseline_int.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', sys.stdin.read()))
