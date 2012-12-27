import sys
html_template = file('charts-template-str_get_manualfinalLuainternalizedcomposite.html', 'r').read()
file('charts_str_get_final_luainternalized_composite.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', sys.stdin.read()))
