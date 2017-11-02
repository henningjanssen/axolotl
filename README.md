# axolotl

## Configuration
All configuration takes place in `config/config.json`.

For more information about doctrine/database-configuration see <http://doctrine-orm.readthedocs.io/projects/doctrine-dbal/en/latest/reference/configuration.html>

### General configuration
#### appconfig.json
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
system.title | `string` | `axolotl` | any string | yes | What is set in the title right of the `|`. If set to an empty string the `|` will not be displayed
upload.simul | `int` | 3 | Any number greater or equal to 1 | yes | Maximum of simultaneous uploaded chunks
upload.chunksize | `int` | 1 * 1024 * 1024 = 1048576 | Any number greater than 0 | yes | Maximal size of chunks used for uploading files
vendor.company | `string` | *empty string* | any string | yes | The name of the company administrating the system
vendor.mail | `string` | *empty string* | any mail-address | yes | The mail-address of the system-administrator
vendor.name | `string` | *empty string* | any string | yes | The name of the system-administrator
vendor.phone | `string` | *empty string* | any phone-number | yes | The phone-number of the system-administrator
vendor.website | `string` | *empty string* | any URL | yes | The website of the system-administrator

#### sysconfig.json
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.doctrine_driver | `string` | *empty string* | `arr` | no | Driver to use for doctrine
db.driver_options | `string` | *empty string* | See documentation of the database | no | Driver-options-string containing connection-parameters
db.host | `string` | `localhost` | `localhost` or any IP | no | Host-server running the database
db.name | `string` | *empty string* | any string | yes | The name of the used database
db.password | `string` | *empty string* | any string | no | Password to use for db-authentication
db.socket | `string` | *empty string* | Path to valid socket | yes | A valid unix-socket that allows connection to a database
db.user | `string` | *empty string* | any string | only if db.socket is used | The username used to connect to the database
system.base_uri | `string` | *empty string* | any string | yes | *coming soon* No trailing slashes
static_lock | `array` of `string` | `[]` | Array of paths relative to the static-directory | yes | Files inside the static-directory that should not be accessible (403)

### Specific configuration (sysconfig.json)
#### if db.doctrine_driver == pdo_sqlite
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.memory | `bool` | `false` | `true`, `false` | yes | ?
db.path | `string` | *empty string* | ? | ? | ?

#### if db.doctrine_driver is one of pdo_mysql, drizzle_pdo_mysql, mysqli
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.charset | `string` | `utf-8` | any valid charset | yes | The charset used for communication with mysql
db.port | `int` | 3306 | any valid portnumber | yes | The port on which mysql is listening

#### if db.doctrine_driver == pdo_pgsql
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.application_name | `string` | `axolotl` | any string | yes | ?
db.charset | `string` | `utf-8` | any valid charset | yes | The charset used for communication with postgres
db.default_dbname | `string` | `postgres` | any string | yes | ?
db.port | `int` | 5432 | any valid portnumber | yes | The port on which postgres is listening
db.sslmode | `string` | `prefer` | any of `disable`, `allow`, `prefer`, `require`, `verify-ca`, `verify-full` | yes | ?

#### if db.doctrine_driver is one of pdo_oci, oci8
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.charset | `string` | `utf-8` | any valid charset | yes | The charset used for communication with oci
db.instancename | `string` | *empty string* | ? | ? | ?
db.pooled | `bool` | `false` | `true`, `false` | yes | ?
db.port | `int` | 1521 | any valid portnumber | yes | The port on which oci is listening
db.servicename | `string` | value of `db.name` | ? | ? | ?

#### if db.doctrine_driver is one of pdo_sqlsrv, sqlsrv
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.port | `int` | 1433 | any valid portnumber | yes | The port on which sqlsrv is listening

#### if db.doctrine_driver == sqlanywhere
Key | type | default | allowed | optional | Description
--- | --- | --- | --- | --- | ---
db.persistent | `bool` | `false` | `true`, `false` | yes | ?
db.port | `int` | 0 | any valid portnumber | no | The port on which the sql-server is listening
db.server | `string` | *empty string* | ? | no | ?

## Docker
Currently the docker-image can be found at <https://hub.docker.com/r/henningj/axolotl/>.

The docker container is built on top of [webdevops/apache:debian-8](https://hub.docker.com/r/webdevops/apache/) with the newest HHVM and postgresql 9.4 installed.

We use the following file-structure (entries with a star* are volumes):

Path | Content
--- | ---
`/app/`* | your website
`/axl/`* | the axolotl-installation
`/axl/modules`* | here are the modules stored. if you want to exchange the container, mount this volume to save them. module data is stored in the database
`/system-data/` | configurations and init-scripts
`/system-data/apache-vhost.conf`* | virtual host for apache
`/system-data/postgresql/`* | postgresql persistence-folder
`/system-data/setup.hh` | entrypoint and setup-file

## Developing axolotl
Clone the repository and run
```
./getcomposer.sh
hhvm ./composer.phar update
hhvm ./vendor/bin/hh-autoload
```
to install all dependencies.

### Without docker
Install a supported database-server (f.e. postgresql, others are untested) and create a user with a database for axolotl. Update the credentials in you `sysconfig.json`. Then run
```
cd install
./doctrine.sh
hhvm ./create-admin.hh
```

### With docker
Then mount your repository as `/axl`:
```
docker run -dit -p80:80 -p443:443 -v /path/to/repo:/axl:z --name axldev henningj/axolotl
```
You can alternatively build the container yourself:
```
docker build . -t axolotl
docker run -dit -p80:80 -443:443 -v /path/to/repo:/axl:z --name axldev axolotl
```
