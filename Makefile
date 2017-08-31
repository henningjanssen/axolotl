

unit:
	vendor/bin/hackunit ./test/

gen_translations:
	xgettext -kt -k_t --language=PHP src/**/*.php -o -
