<?php

require_once 'string_utils.php';


function parseYesNo($text, $language_code = '')
{
	if ($language_code == '')
		$language_code = outputValueGet('language_code');
	if ($language_code == '')
		$language_code = settingGet('language_code');
	if ($language_code == '')
		$language_code = 'en';

	static $data = [
		'en' => [
			'yes' => 'y',
			'no'  => 'n'
		],
        'da' => [
            'ja'  => 'y',
            'nej' => 'n'
        ],
        'de' => [
            'ja'  => 'y',
            'nein' => 'n'
        ],
        'fr' => [
            'oui'  => 'y',
            'non' => 'n'
        ],
        'nl' => [
            'ja'  => 'y',
            'nee' => 'n'
        ],
        'pl' => [
            'tak'  => 'y',
            'nie' => 'n'
        ],
        'nb' => [
            'ja'  => 'y',
            'nei' => 'n'
        ],
        'sv' => [
            'ja'  => 'y',
            'nej' => 'n'
        ]

	];

	$lookup = $data[$language_code];
	
	$textLower = str_to_lower($text);
	$tok = strtok($textLower, WORD_DELIMETERS);
	
	$val = '';
	while ($tok !== false) {
		$val = getArraySafe( $tok, $lookup, '' );
		if ($val != '')
			break;
		$tok = strtok(WORD_DELIMETERS);
	}
	return $val;
}

