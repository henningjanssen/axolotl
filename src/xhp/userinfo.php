<?php

use \axolotl\entities\User;

class :axolotl:xhp:userinfo extends :x:element{
	attribute
		User user @required,
		string dateFormat = "d.m.Y H:i",
		?string title = null;

		children (:bootstrap:list-group-item*);

		protected function render(): \XHPRoot{
	    return <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          {$this->:title ?? t('User')}
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              {t('Username')}: {$this->:user->getUsername()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('E-Mail')}: {$this->:user->getEmail()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Full Name')}: {$this->:user->getFullName()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Account-Note')}: {$this->:user->getNote()}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Registered')}:
								{$this->:user->getRegistration()->format($this->:dateFormat)}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Last activity')}:
								{$this->:user->getLastActivity()->format($this->:dateFormat)}
            </bootstrap:list-group-item>
						{$this->getChildren()}
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>;
		}
}
