from xbuild.declare import *

XBuild(
    name='x_log_interface'
).add(
    CppTarget('x.log.interface', TargetType.HeadersOnly)
    .public_include_dirs([
        XPath.path('public_include')
    ])
)