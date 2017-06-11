<?hh // strict

use \axolotl\entities\User;

class :axolotl:xhp:userinfo extends :x:element{
	attribute
		User user @required,
		string dateFormat = "d.m.Y H:i";

		children (:bootstrap:list-group-item*);

		protected function render(): \XHPRoot{
	    return <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          Installed by
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              Username: {$this->:user->getUsername()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              E-Mail: {$this->:user->getEmail()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Full Name: {$this->:user->getFullName()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Account-Note: {$this->:user->getNote()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Registered:
								{$this->:user->getRegistration()->format($this->:dateFormat)}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              Last activity:
								{$this->:user->getLastActivity()->format($this->:dateFormat)}
            </bootstrap:list-group-item>
						{$this->getChildren()}
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>;
		}
}
