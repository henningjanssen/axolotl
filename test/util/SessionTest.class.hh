<?hh // strict

namespace axolotl\test\util;

require_once __DIR__.'/../../vendor/autoload.php';

use \HackPack\HackUnit\Contract\Assert;
use axolotl\util\_;
use axolotl\util\Session;

class SessionTest{
  <<Test>>
  public async function test(Assert $assert): Awaitable<void>{
    $save = _::SESSION("uid");
    if($save === null){
      $assert->bool(Session::loggedIn())->is(false);
    }
    _::SESSION("uid", 42);
    $assert->bool(Session::loggedIn())->is(true);

    Session::logout();
    $assert->bool(Session::loggedIn())->is(false);

    if($save !== null){
      _::SESSION("uid", $save);
    }
  }
}
