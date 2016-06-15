-e #!/bin/sh
exec "`dirname "$0"`/configure" --disable-install-jim "$@"
