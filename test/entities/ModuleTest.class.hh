<?hh // strict

namespace axolotl\test\entities;

require_once __DIR__.'/../../vendor/autoload.php';
require_once __DIR__.'/../../src/entities/Module.class.hh';
require_once __DIR__.'/../../src/entities/User.class.hh';

use \HackPack\HackUnit\Contract\Assert;
use \axolotl\entities\Module;
use \axolotl\entities\User;
use \axolotl\exceptions\InvalidArgumentException;

class ModuleTest{
  private User $exampleUser;
  private Module $module;

  public function __construct(){
    $this->exampleUser = User::newInstance(
      "timothy.test@example.org",
      "Timothy Test",
      hash("sha256", "testpass"),
      true,
      "Never gonna give you up",
      new \DateTime("@-1815350400", new \DateTimeZone("Europe/Berlin")),
      new \DateTime("@1463576124", new \DateTimeZone("Europe/Berlin"))
    );
    $this->module = Module::newInstance(
      "Astley",
      new \DateTime("@102556800", new \DateTimeZone("Europe/Berlin")),
      $this->exampleUser
    );
  }

  <<Setup('test')>>
  public function setUp(): void{
    $this->module = Module::newInstance(
      "Astley",
      new \DateTime("@102556800", new \DateTimeZone("Europe/Berlin")),
      $this->exampleUser
    );
  }

  <<Test>>
  public function testName(Assert $assert): void{
    $assert->string($this->module->getName())->is("Astley");
    $this->module->setName("Jan");
    $assert->string($this->module->getName())->is("Jan");

    try{
      $this->module->setName(" \t ");
      $assert->bool(true)->is(false);
    }
    catch(InvalidArgumentException $iaex){}
  }

  <<Test>>
  public function testInstallationDate(Assert $assert): void{
    $assert->mixed($this->module->getInstallationDate())->isTypeOf("\DateTime");
    $assert->mixed($this->module->getInstallationDate())->looselyEquals(
      new \DateTime("@102556800", new \DateTimeZone("Europe/Berlin"))
    );

    $time = time();
    $this->module->setInstallationDate(null);
    $assert->mixed($this->module->getInstallationDate())->isTypeOf("\DateTime");
    $assert->mixed($this->module->getInstallationDate())->looselyEquals(
      new \DateTime("@$time", new \DateTimeZone("Europe/Berlin"))
    );
  }

  <<Test>>
  public function testCreator(Assert $assert): void{
    $assert->mixed($this->module->getCreator())->identicalTo($this->exampleUser);

    $user = User::newInstance(
      "a.b@example.org",
      "ab",
      hash("sha256", "testpass"),
      true,
      "ea",
      new \DateTime("@-1815350400", new \DateTimeZone("Europe/Berlin")),
      new \DateTime("@1463576124", new \DateTimeZone("Europe/Berlin"))
    );
    $this->module->setCreator($user);
    $assert->mixed($this->module->getCreator())->not()->identicalTo(
      $this->exampleUser
    );
    $assert->mixed($this->module->getCreator())->identicalTo($user);
  }
}