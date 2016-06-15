-e #!/bin/sh
exec "`dirname "$0"`/configure" --enable-subproject-build "$@"
