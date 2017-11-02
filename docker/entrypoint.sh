hhvm /system-data/setup.hh
#su application -c "hhvm --mode daemon -d hhvm.server.type=fastcgi -d hhvm.server.port=9000 -vServer.AllowRunAsRoot=1 -d hhvm.log.file=/system-data/hhvm.log -d hhvm.log.use_log_file=true" &
supervisord
