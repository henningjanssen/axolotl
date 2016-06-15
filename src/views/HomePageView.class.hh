<?hh // strict

use axolotl\entities\User;

class HomePageView extends PageView{
  public function __construct(
    User $user
  ){
    parent::__construct("Home");
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          User information
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              Username: {$user->getUsername()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              E-Mail: {$user->getEmail()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Full Name: {$user->getFullName()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Account-Note: {$user->getNote()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Registered: {$user->getRegistration()->format("d.m.Y H:i")}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Last activity: {$user->getLastActivity()->format("d.m.Y H:i")}
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
  }
}
