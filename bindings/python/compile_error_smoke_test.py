import postanvil


source = '''
RULE FILTER "person":
    self.conf >= 0.5
    OR self.area > 10
RULEEND
'''.lstrip()

try:
    postanvil.compile(source)
except postanvil.PACompileError as error:
    text = str(error)
    assert "line 3, column 5" in text
    assert "OR self.area" in text
    assert "help:" in text
    assert "expecting {" not in text
    print(text)
else:
    raise AssertionError("Expected postanvil.PACompileError")
