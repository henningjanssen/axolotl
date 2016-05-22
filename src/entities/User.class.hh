<?hh // strict

namespace axolotl\entities;

/**
 * @Entity
 * @Table(name="users")
 */
class User{
  /** @Id @Column(type="Integer") @GeneratedValue */
  protected int $id;

  /** @Column(type="string", length=32, unique=true, nullable=false)*/
  protected string $username;

  /** @Column(type="text") */
  protected string $email;

  /** @Column(type="text", name="full_name") */
  protected string $fullName;

  /** @Column(type="string", length="64") */
  protected string $password;

  /** @Column(type="text") */
  protected string $note;

  /** @Column(type="datetimetz") */
  protected \DateTime $registration;

  /** @Column(type="datetimetz", name="last_activity") */
  protected \DateTime $lastActivity;

  /** @OneToMany(targetEntity="Module", mappedBy="creator") */
  protected array<Module> $installedModules;

  //Needed for the hack typechecker
  public function __construct(){
    $this->id = -1;
    $this->username = "";
    $this->email = "";
    $this->fullName = "";
    $this->password = "";
    $this->note = "";
    $this->registration = new \DateTime(
      "@".time(), new \DateTimeZone("Europe/Berlin")
    );
    $this->lastActivity = new \DateTime(
      "@".time(), new \DateTimeZone("Europe/Berlin")
    );
    $this->installedModules = array();
  }

  //Not possible as a constructor as polymorfic method-overloading
  //is not possible
  public static function newInstance(
    string $mail, string $username, string $fullName, string $password,
    bool $pwHashed, string $note, ?\DateTime $registration,
    ?\DateTime $lastActivity
  ): User{
    $user = new User();
    $user->setEmail($mail);
    $user->setUsername($username);
    $user->setFullName($fullName);
    $user->setPassword($password, $pwHashed);
    $user->setNote($note);
    $user->setRegistration($registration);
    $user->setLastActivity($lastActivity);
    return $user;
  }

  public function getID(): int{
    return $this->id;
  }

  public function setEmail(string $mail): void{
    if(!filter_var($mail, FILTER_VALIDATE_EMAIL)){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Malformed e-mail-adress: $mail"
      );
    }
    $this->email = $mail;
  }
  public function getEmail(): string{
    return $this->email;
  }

  public function setUsername(string $username): void{
    $username = trim($username);
    if(strlen($username) === 0){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Username is empty"
      );
    }
    $this->username = $username;
  }
  public function getUsername(): string{
    return $this->username;
  }

  public function setFullName(string $fullname): void{
    $fullname = trim($fullname);
    if(strlen($fullname) === 0){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Full name is empty"
      );
    }
    $this->fullName = $fullname;
  }
  public function getFullName(): string{
    return $this->fullName;
  }

  public function setPassword(string $pw, bool $isHashed = true): void{
    if($isHashed){
      if(strlen($pw) !== 64){
        throw new \axolotl\exceptions\InvalidArgumentException(
          "Password hash has wrong length. Did you use sha256?"
        );
      }
    }
    else{
      $pw = hash("sha256", $pw);
    }
    $this->password = $pw;
  }
  public function getPassword(): string{
    return $this->password;
  }

  public function setNote(string $note): void{
    $this->note = $note;
  }
  public function getNote(): string{
    return $this->note;
  }

  public function setRegistration(?\DateTime $reg = null): void{
    if($reg === null){
      $reg = new \DateTime("@".time(), new \DateTimeZone("Europe/Berlin"));
    }
    invariant($reg !== null, "User::setRegistration: \$reg is null");
    $this->registration = $reg;
  }
  public function getRegistration(): \DateTime{
    return $this->registration;
  }

  public function setLastActivity(?\DateTime $la = null): void{
    if($la === null){
      $la = new \DateTime("@".time(), new \DateTimeZone("Europe/Berlin"));
    }
    invariant($la !== null, "User::setRegistration: \$la is null");
    $this->lastActivity = $la;
  }
  public function getLastActivity(): \DateTime{
    return $this->lastActivity;
  }
}
