<?hh // strict

namespace axolotl\test\util;

require_once __DIR__.'/../../vendor/autoload.php';

use \HackPack\HackUnit\Contract\Assert;
use axolotl\test\Util;
use axolotl\exceptions\BrokenInstallationException;
use axolotl\util\_;

class _Test{
  <<Test>>
  public async function testGET(Assert $assert): Awaitable<void>{
    $save = Util::getGET();
    $val = array("Slinky" => "Dog", "Specky" => "Hamm");
    Util::setGET($val);
    foreach(array_keys($val) as $key){
      $assert->mixed(_::GET($key))->looselyEquals($val[$key]);
    }
    $assert->mixed(_::GET("null_key"))->isNull();
    Util::setGET($save);
  }

  <<Test>>
  public async function testPOST(Assert $assert): Awaitable<void>{
    $save = Util::getPOST();
    $val = array("Potato" => "Head", "Bo" => "Peep");
    Util::setPOST($val);
    foreach(array_keys($val) as $key){
      $assert->mixed(_::POST($key))->looselyEquals($val[$key]);
    }
    $assert->mixed(_::POST("null_key"))->isNull();
    Util::setPOST($save);
  }

  <<Test>>
  public async function testSERVER(Assert $assert): Awaitable<void>{
    $save = Util::getSERVER();
    $val = Util::getSERVER() ?? array();
    $val["Rex"] = "NoSurname";
    $val["Hannah"] = "Davis";
    Util::setSERVER($val);
    foreach(array_keys($val) as $key){
      $assert->mixed(_::SERVER($key))->looselyEquals($val[$key]);
    }
    $assert->mixed(_::SERVER("null_key"))->isNull();
    Util::setSERVER($save);
  }

  <<Test>>
  public async function testSESSION(Assert $assert): Awaitable<void>{
    _::SESSION("Rex", "NoSurname");
    _::SESSION("Hannah", "Davis");
    _::SESSION("Woody", "McWoodface");
    $assert->mixed(_::SESSION("Rex"))->looselyEquals("NoSurname");
    $assert->mixed(_::SESSION("Hannah"))->looselyEquals("Davis");
    $assert->mixed(_::SESSION("Woody"))->looselyEquals("McWoodface");
    $assert->mixed(_::SESSION("null_key"))->isNull();
  }

  <<Test>>
  public async function testSETTINGS(Assert $assert): Awaitable<void>{
    $path = realpath(__DIR__.'/../../config/config.json');
    $save = "";
    $exists = file_exists($path);
    if($exists){
      $save = file_get_contents($path);
    }
    $val = array("Ms"=>"Davis", "Buzz"=>"Lightyear");
    file_put_contents($path, json_encode($val));
    _::reloadSettings();
    foreach(array_keys($val) as $key){
      $assert->mixed(_::SETTINGS($key))->looselyEquals($val[$key]);
    }
    $assert->mixed(_::SETTINGS("null_key"))->isNull();

    file_put_contents($path, "{}");
    try{
      _::reloadSettings();
      $assert->bool(true)->is(false);
    }
    catch(BrokenInstallationException $biex){}

    file_put_contents($path, "afsf");
    try{
      _::reloadSettings();
      $assert->bool(true)->is(false);
    }
    catch(BrokenInstallationException $biex){}

    unlink($path);
    try{
      _::reloadSettings();
      $assert->bool(true)->is(false);
    }
    catch(BrokenInstallationException $biex){}

    if($exists){
      file_put_contents($path, $save);
      _::reloadSettings();
    }
  }
}
