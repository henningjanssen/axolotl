<?hh // partial

require_once __DIR__.'/vendor/autoload.php';

use axolotl\control\ApplicationControl;

(new ApplicationControl(_::SERVER['REQUEST_METHOD'], _::SERVER['REQUEST_URI']))
  ->execute();
