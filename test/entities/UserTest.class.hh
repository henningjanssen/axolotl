<?hh // strict

namespace axolotl\test\entities;

require_once __DIR__.'/../../vendor/autoload.php';
require_once __DIR__.'/../../src/entities/User.class.hh';

use \HackPack\HackUnit\Contract\Assert;
use \axolotl\entities\User;

class UserTest{
  private \axolotl\entities\User $user;

  public function __construct(){
    $this->user = User::newInstance(
      "timothy.test@example.org",
      "Timothy Test",
      hash("sha256", "testpass"),
      true,
      "Never gonna give you up",
      new \DateTime("@-1815350400", new \DateTimeZone("Europe/Berlin")),
      new \DateTime("@1463576124", new \DateTimeZone("Europe/Berlin"))
    );
  }

  <<Setup('test')>>
  public function setUp(): void{
    $this->user = User::newInstance(
      "timothy.test@example.org",
      "Timothy Test",
      hash("sha256", "testpass"),
      true,
      "Never gonna give you up",
      new \DateTime("@-1815350400", new \DateTimeZone("Europe/Berlin")),
      new \DateTime("@1463576124", new \DateTimeZone("Europe/Berlin"))
    );
  }

  <<Test>>
  public function testMail(Assert $assert): void{
    $assert->string($this->user->getEmail())->is("timothy.test@example.org");
    $this->user->setEmail("test@test.org");
    $assert->string($this->user->getEmail())->is("test@test.org");

    try{
      $this->user->setEmail("testtest.org");
      $assert->bool(true)->is(false);
    }
    catch(\axolotl\exceptions\InvalidArgumentException $iaex){}

    try{
      $this->user->setEmail("@test.org");
      $assert->bool(true)->is(false);
    }
    catch(\axolotl\exceptions\InvalidArgumentException $iaex){}
  }

  <<Test>>
  public function testFullName(Assert $assert): void{
    $assert->string($this->user->getFullName())->is("Timothy Test");
    $this->user->setFullName("Rick");
    $assert->string($this->user->getFullName())->is("Rick");

    try{
      $this->user->setFullName("");
      $assert->bool(true)->is(false);
    }
    catch(\axolotl\exceptions\InvalidArgumentException $iaex){}

    try{
      $this->user->setFullName(" \t ");
      $assert->bool(true)->is(false);
    }
    catch(\axolotl\exceptions\InvalidArgumentException $iaex){}
  }

  <<Test>>
  public function testPassword(Assert $assert): void{
    $assert->string($this->user->getPassword())->is(hash("sha256", "testpass"));

    $pw = hash("sha256", "nevergonnaletyoudown");
    $this->user->setPassword($pw);
    $assert->string($this->user->getPassword())->is($pw);

    $pw = "nevergonnamakeyoucry";
    $this->user->setPassword($pw, false);
    $assert->string($this->user->getPassword())->is(hash("sha256", $pw));

    try{
      $this->user->setPassword("or hurt you");
      $assert->bool(true)->is(false);
    }
    catch(\axolotl\exceptions\InvalidArgumentException $iaex){}
  }

  <<Test>>
  public function testRegistration(Assert $assert): void{
    $assert->mixed($this->user->getRegistration())->isTypeOf("\DateTime");
    $assert->mixed($this->user->getRegistration())->looselyEquals(
      new \DateTime("@-1815350400", new \DateTimeZone("Europe/Berlin"))
    );

    $time = time();
    $this->user->setRegistration(null);
    $assert->mixed($this->user->getRegistration())->isTypeOf("\DateTime");
    $assert->mixed($this->user->getRegistration())->looselyEquals(
      new \DateTime("@$time", new \DateTimeZone("Europe/Berlin"))
    );
  }

  <<Test>>
  public function testLastActivity(Assert $assert): void{
    $assert->mixed($this->user->getLastActivity())->isTypeOf("\DateTime");
    $assert->mixed($this->user->getLastActivity())->looselyEquals(
      new \DateTime("@1463576124", new \DateTimeZone("Europe/Berlin"))
    );

    $time = time();
    $this->user->setLastActivity(null);
    $assert->mixed($this->user->getLastActivity())->isTypeOf("\DateTime");
    $assert->mixed($this->user->getLastActivity())->looselyEquals(
      new \DateTime("@$time", new \DateTimeZone("Europe/Berlin"))
    );
  }
}
