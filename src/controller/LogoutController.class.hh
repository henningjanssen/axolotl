<?hh // strict

namespace axolotl\controller;

use \RedirectView;
use axolotl\util\Session;

class LogoutController extends PageController{
  public function execute(): void{
    Session::logout();
    (new RedirectView("/login"))->render();
  }
}
