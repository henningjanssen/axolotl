<?php

namespace axolotl\entities;

use axolotl\exceptions\EntityNotFoundException;
use axolotl\util\Doctrine;
use axolotl\util\Log;

/**
 * @Entity
 * @Table(name="users")
 */
class User{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected $id;

  /** @Column(type="string", length=32, unique=true, nullable=false)*/
  protected $username;

  /** @Column(type="text", unique=true, nullable=false) */
  protected $email;

  /** @Column(type="text", name="full_name") */
  protected $fullName;

  /** @Column(type="string", length=60) */
  protected $password;

  /** @Column(type="text") */
  protected $note;

  /** @Column(type="datetimetz") */
  protected $registration;

  /** @Column(type="datetimetz", name="last_activity") */
  protected $lastActivity;

  /**
  * @OneToMany(targetEntity="Module", mappedBy="creator")
  */
  protected $installedModules;

  /** @Column(type="string", length=5) */
  protected $language;

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
    $this->language = null;
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

  public static function getByLogin(string $login): User{
		$entityManager = Doctrine::getEntityManager();
    $qb = $entityManager->createQueryBuilder();
		$query = $qb->select('u')
			->from(User::class, 'u')
			->where(
				$qb->expr()->orX(
					$qb->expr()->eq('u.email', ':login'),
					$qb->expr()->eq('u.username', ':login')
				)
			)
			->setParameter('login', $login)
			->getQuery();
		try{
			$user = $query->getSingleResult();
      return $user;
		}
		catch(\Doctrine\ORM\NoResultException $nrex){
			Log::error('User::getByLogin',
				"User not found. Query: `{$query->getSQL()}`"
				.", login: `{$login}`"
			);
      throw new EntityNotFoundException("User {$login} not found");
		}
  }

  public function getID(): int{
    return $this->id;
  }

  public function setEmail(string $mail): User{
    if(!filter_var($mail, FILTER_VALIDATE_EMAIL)){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Malformed e-mail-adress: $mail"
      );
    }
    $this->email = $mail;
    return $this;
  }
  public function getEmail(): string{
    return $this->email;
  }

  public function setUsername(string $username): User{
    $username = trim($username);
    if(strlen($username) === 0){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Username is empty"
      );
    }
    $this->username = $username;
    return $this;
  }
  public function getUsername(): string{
    return $this->username;
  }

  public function setFullName(string $fullname): User{
    $fullname = trim($fullname);
    if(strlen($fullname) === 0){
      throw new \axolotl\exceptions\InvalidArgumentException(
        "Full name is empty"
      );
    }
    $this->fullName = $fullname;
    return $this;
  }
  public function getFullName(): string{
    return $this->fullName;
  }

  public function setPassword(string $pw, bool $isHashed = true): User{
    if(!$isHashed){
      $pw = strval(password_hash($pw, PASSWORD_BCRYPT));
    }
    $this->password = $pw;
    return $this;
  }
  public function getPassword(): string{
    return $this->password;
  }

  public function setNote(string $note): User{
    $this->note = $note;
    return $this;
  }
  public function getNote(): string{
    return $this->note;
  }

  public function setRegistration(?\DateTime $reg = null): User{
    if($reg === null){
      $reg = new \DateTime("@".time(), new \DateTimeZone("Europe/Berlin"));
    }
    invariant($reg !== null, "User::setRegistration: \$reg is null");
    $this->registration = $reg;
    return $this;
  }
  public function getRegistration(): \DateTime{
    return $this->registration;
  }

  public function setLastActivity(?\DateTime $la = null): User{
    if($la === null){
      $la = new \DateTime("@".time(), new \DateTimeZone("Europe/Berlin"));
    }
    invariant($la !== null, "User::setLastActivity: \$la is null");
    $this->lastActivity = $la;
    return $this;
  }
  public function getLastActivity(): \DateTime{
    return $this->lastActivity;
  }

  public function setLanguage(string $language): User {
    $this->language = $language;
    return $this;
  }

  public function getLanguage(string $default = 'en'): string {
    return $this->language ?? $default;
  }
}
