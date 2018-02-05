<?php

use \axolotl\util\_;
use \axolotl\util\AXLSettingsFile;

class AboutView extends PageView{
  public function __construct(
    //
  ){
    parent::__construct(t("About"));
    $vendorWebsite = strval(
      _::SETTINGS("vendor.website", "", _::SETTINGS_APP)
    );
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          {t('Vendor')}
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              {t('Vendor')}:
              {_::SETTINGS("vendor.name", "", _::SETTINGS_APP)}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Support E-Mail')}:
              {_::SETTINGS("vendor.mail", "", _::SETTINGS_APP)}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item>
              {t('Support Phone')}:
              {_::SETTINGS("vendor.phone", "", _::SETTINGS_APP)}
            </bootstrap:list-group-item>
            <bootstrap:list-group-item href={$vendorWebsite} target="_blank">
              {t('Website')}: {$vendorWebsite}
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
    $this->content->appendChild(
      <bootstrap:panel use="info">
        <bootstrap:panel:heading>
          {t('About this project')}
        </bootstrap:panel:heading>
        <bootstrap:panel:body>
          <bootstrap:list-group>
            <bootstrap:list-group-item>
              {t('Project-Name')}: axolotl
            </bootstrap:list-group-item>
            <bootstrap:list-group-item
              href="http://github.com/henningjanssen/axolotl" target="_blank"
            >
              {t('Project on Github')}: http://github.com/henningjanssen/axolotl
            </bootstrap:list-group-item>
          </bootstrap:list-group>
        </bootstrap:panel:body>
      </bootstrap:panel>
    );
  }
}
