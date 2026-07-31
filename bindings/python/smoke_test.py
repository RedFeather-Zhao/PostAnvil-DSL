import postanvil


source = """
RULE FILTER "global":
    self.conf >= 0.5
RULEEND
"""

scene = postanvil.Scene(
    postanvil.Image(100, 100),
    [
        postanvil.Instance("person", 0, 0, 10, 10, 0.8),
        postanvil.Instance("person", 0, 0, 10, 10, 0.2),
    ],
)
result = postanvil.compile(source).evaluate(scene)

assert result.count("PERSON") == 1
print(f"PostAnvil {postanvil.__version__}: Python smoke test passed")
