<?php
require_once "string_utils.php";

/** Debug loggging class.*/
class CrawlerLog
{
    // Logging categories.
    const NONE      = 0;
    const ERROR     = 1;
    const WARNING   = 2;
    const INFO      = 4;
    const PROGRESS  = 8;
    const DEBUG     = 16;
    const ALL       = PHP_INT_MAX;

    
    /** Write to log. Only write to log if \a $category is in the current set of 
    logging categories as set with DLog::loggingCategoriesSet()
    \a $category The loggging category. Use one of the constanst above. 
    \a $format Format string as known from printf.
    \a args... Variable number of arguments as known from printf. */
    public function clog()
    {
        $argv = func_get_args();
        if (count($argv) < 2) return;
        $category = (int)(array_shift( $argv ));
        if ($category & $this->loggingCategories()) {
            $format = array_shift( $argv );
            print self::categoryValueToName($category) . ' : ';
            vprintf( $format, $argv );
        }
    }
    
    
    public function loggingCategoriesSet($categories) 
    {
        if (is_string($categories)) {
            $catMask = self::categoriesMaskFromString($categories); 
            $this->m_loggingCategories = $catMask;
        }
        else {
            $this->m_loggingCategories = $categories;
        }
    }

    public function loggingCategoriesSetNone() 
    {
        $this->m_loggingCategories = self::NONE;
    }

    public function loggingCategoriesSetError() 
    {
        $this->m_loggingCategories = self::ERROR;
    }

    public function loggingCategoriesSetWarning() 
    {
        $this->m_loggingCategories = self::WARNING;
    }
    
    public function loggingCategoriesSetInfo() 
    {
        $this->m_loggingCategories = self::INFO;
    }

    public function loggingCategoriesSetProgress() 
    {
        $this->m_loggingCategories = self::PROGRESS;
    }

    public function loggingCategoriesSetDebug() 
    {
        settingSet("dbg_sitemaps", "true");
        $this->m_loggingCategories = self::DEBUG;
    }

    public function loggingCategoriesSetAll() 
    {
        $this->m_loggingCategories = self::ALL;
    }

    public function loggingCategoriesSetDefault() 
    {
        $this->m_loggingCategories = self::ERROR | self::PROGRESS;
    }
    
    public function loggingCategories() 
    {
        return (int)$this->m_loggingCategories;
    }

    public function loggingCategoriesPrintMask() 
    {
        printf("Logging categories mask: %X\n", $this->loggingCategories() );
    }
    
    public static function I()
    {
        if (CrawlerLog::$m_instance == null) {
            CrawlerLog::$m_instance = new CrawlerLog();
        }
        return CrawlerLog::$m_instance;
    }
    
    public static function categoryValueToName($category)
    {
        return self::$m_catValueToName[$category];
    }
    
    public static function categoryNameToValue($categoryName)
    {
        return self::$m_catNameToValue[$categoryName];
    }
    
    public static function categoriesMaskFromString($categoriesCommaSeparated) 
    {
        $mask = 0;
        $a = explodeTrim(',', $categoriesCommaSeparated);
        foreach ($a as $categoryName) {
            $m = @self::$m_catNameToValue[$categoryName];
            if ($m != '') {
                $mask |= $m;
            }
        }
        
        return $mask;
    }
    
    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    private static $m_instance = null;
    private $m_loggingCategories = self::ERROR;
    private static $m_catValueToName = array (
          self::NONE        => 'NONE'
        , self::ERROR       => 'ERROR'
        , self::WARNING     => 'WARNING'
        , self::INFO        => 'INFO'
        , self::PROGRESS    => 'PROGRESS'
        , self::DEBUG       => 'DEBUG'
        , self::ALL         => 'ALL'
    );

    private static $m_catNameToValue = array (
          'NONE'        => self::NONE
        , 'ERROR'       => self::ERROR
        , 'WARNING'     => self::WARNING
        , 'INFO'        => self::INFO
        , 'PROGRESS'    => self::PROGRESS
        , 'DEBUG'       => self::DEBUG
        , 'ALL'         => self::ALL
    );
    
}

function clog()
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "clog"), $argv);
}


function clogLevels($categories) 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSet"), $argv);
}
    

function clogLevelsNone() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetNone"), $argv);
}

function clogLevelsError() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetError"), $argv);
}

function clogLevelsWarning() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetWarning"), $argv);
}

function clogLevelsInfo() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetInfo"), $argv);
}
    
function clogLevelsProgress() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetProgress"), $argv);
}

function clogLevelsDebug() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetDebug"), $argv);
}

function clogLevelsAll() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetAll"), $argv);
}

function clogLevelsDefault() 
{
    $argv = func_get_args();
    call_user_func_array(array(CrawlerLog::I(), "loggingCategoriesSetDefault"), $argv);
}

