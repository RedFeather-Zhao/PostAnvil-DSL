import postanvil


source = '''
RULE FILTER "person" {
    self.conf >= 0.5
    OR self.area > 10
}
'''.lstrip()

try:
    postanvil.compile(source)
except postanvil.PACompileError as error:
    text = str(error)
    assert error.kind == postanvil.CompileErrorKind.SYNTAX
    assert error.message
    assert error.line == 3
    assert error.column == 5
    assert error.source_line == "    OR self.area > 10"
    assert error.hint
    assert error.raw_message
    assert "line 3, column 5" in text
    assert "OR self.area" in text
    assert "help:" in text
    assert "expecting {" not in text
    print(text)
else:
    raise AssertionError("Expected postanvil.PACompileError")
