<?php



class UnitTestBase
{


    // ------------------------
    // --- Constructor init --- 
    // ------------------------
    public function __construct( $mainTestName )
    {
        $this->m_mainTestName   = $mainTestName;
        $this->m_subTestName    = '';
        $this->m_countCorrect   = 0;
        $this->m_countError     = 0;
    }

    public function __destruct()
    {
        if ($this->countError() != 0) {
            printf ("\n%d ERRORS found in test! Total tests: %d.\n\n", $this->countError(), $this->countTotal() );
        }
        else {
            printf ("\nSUCCESS!\n\t%d test cases executed correctly!\n\n", $this->countCorrect(), $this->countTotal() );
        }
    }

    public function run()
    {
        print "Error override me! ";
    }
    
    

    final public function checkEqual($actual, $expected)
    {
        if ($actual == $expected) $this->m_countCorrect++;
        else {
            $this->m_countError++;
            printf("\nError '%s::%s::checkEqual()' =>\n'$actual'\n!=\n'$expected'\n\n", $this->testName(), $this->subTestName());
        }
    }

    final public function checkAssocHas($aActual, $aHasAtLeast)
    {
		$aNotMatch = array();
        $ok = true;
        foreach ($aHasAtLeast as $key => $val) {
			if (@$aActual[$key] != $val) {
				$ok = false;
				$aNotMatch[$key] = array(@$aActual[$key], $val);
				break;
			}
        }
        
        
        if ($ok) $this->m_countCorrect++;
        else {
            $this->m_countError++;
            $actual = json_encode( $aActual, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES );
            $expected = json_encode( $aHasAtLeast, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES );
            $notMatch = json_encode( $aNotMatch, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES );
            
            printf("Error 'checkAssocHas()' =>\n'$actual'\n!=\n'$expected'\nTEST: %s::%s\nNOT MATCH:'$notMatch'\n\n", $this->testName(), $this->subTestName());
        }
    }

    final public function testName()      {  return $this->m_mainTestName;  }
    final public function subTestName()   {  return $this->m_subTestName;   }
    final public function countCorrect()  {  return $this->m_countCorrect;  }
    final public function countError()    {  return $this->m_countError;    }
    final public function countTotal()    {  return $this->m_countCorrect + $this->m_countError;   }

    final public function subTestNameSet    ($subTestName)      {  return $this->m_subTestName = $subTestName;    }
    
    private $m_mainTestName;
    private $m_countCorrect;
    private $m_countError;
    private $m_subTestName;

}    
    
?>