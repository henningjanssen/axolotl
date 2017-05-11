# axolotl

## Configuration
All configuration takes place in `config/config.json`.

For more information about doctrine/database-configuration see <http://doctrine-orm.readthedocs.io/projects/doctrine-dbal/en/latest/reference/configuration.html>

### General configuration
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
system.title | `string` | `axolotl` | any string | yes | What is set in the title right of the `|`. If set to an empty string the `|` will not be displayed
static_lock | `array` of `string` | `[]` | Array of paths relative to the static-directory | yes | Files inside the static-directory that should not be accessible (403)
upload.chunksize | `int` | 1 * 1024 * 1024 = 1048576 | Any number greater than 0 | yes | Maximal size of chunks used for uploading files
upload.simul | `int` | 3 | Any number greater or equal to 1 | yes | Maximum of simultaneous uploaded chunks
vendor.company | `string` | *empty string* | any string | yes | The name of the company administrating the system
vendor.mail | `string` | *empty string* | any mail-address | yes | The mail-address of the system-administrator
vendor.name | `string` | *empty string* | any string | yes | The name of the system-administrator
vendor.phone | `string` | *empty string* | any phone-number | yes | The phone-number of the system-administrator
vendor.website | `string` | *empty string* | any URL | yes | The website of the system-administrator

### Specific configuration
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
