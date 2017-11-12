<?hh // partial

require_once __DIR__.'/../src/global_functions.php';
require_once __DIR__.'/../axl-autoload.php';

use axolotl\control\ApplicationControl;
use axolotl\util\_;

(new ApplicationControl(_::SERVER('REQUEST_URI'), _::SERVER('REQUEST_METHOD')))
  ->execute();
