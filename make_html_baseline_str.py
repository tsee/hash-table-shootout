import sys
html_template = file('charts-template-baseline_str.html', 'r').read()
file('charts_baseline_str.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', sys.stdin.read()))
