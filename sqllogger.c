#include <stdio.h>

int main(int argc, char* argv[]) {

    printf("This is my bin file\n");

    /*char* validCommands[] = {
        "EXECUTE",
        "QUERY"
    };

    char* validVerbs[] = {
        "SELECT",
        "INSERT",
        "DELETE",
        "UPDATE"
    };*/

    

}    



/*require 'Colors.php';

class ChecmicalLeakLogger {

    private $lastCommand = null;
    private $lastVerb = null;
    private $validCommands = [
        'EXECUTE',
        'QUERY'
    ];

    private $validVerbs = [
        'SELECT',
        'INSERT',
        'DELETE',
        'UPDATE'
    ];

    protected $colors = null;

    public function test() {
        $colors = new Colors();

        // Get Foreground Colors
        $fgs = $colors->getForegroundColors();
        // Get Background Colors
        $bgs = $colors->getBackgroundColors();

        // Loop through all foreground and background colors
        $count = count($fgs);
        for ($i = 0; $i < $count; $i++) {
            echo $colors->getColoredString("Test Foreground colors", $fgs[$i]) . "$fgs[$i]". "\t";
            if (isset($bgs[$i])) {
                echo $colors->getColoredString("Test Background colors", null, $bgs[$i]);
            }
            echo "\n";
        }
        echo "\n";

        // Loop through all foreground and background colors
        foreach ($fgs as $fg) {
            foreach ($bgs as $bg) {
                echo $colors->getColoredString("Test Colors", $fg, $bg) . "\t";
            }
            echo "\n";
        }
    }

    public function run($fileName) {

        $this->colors = new Colors();

        $handle = fopen($fileName, 'r');

        if ($handle) {
            while (($line = fgets($handle)) !== false) {

                $matches = [];

                //line with timestamp
                if (preg_match('/^\d{6}\s\d{2}:\d{2}:\d{2}\s+\d+\s+([a-zA-Z]+)\s*(\S*)(\s\X*)/', $line, $matches)) {
                    $this->lastCommand = $matches[1];
                    $this->lastVerb = $matches[2] ?? '';
                    $sql = $this->lastVerb . ($matches[3] ?? '');
                } else if (preg_match('/^\s+\d+\s+([a-zA-Z]+)\s+([a-zA-Z]+)(\X+)/', $line, $matches)){
                    $this->lastCommand = $matches[1];
                    $this->lastVerb = $matches[2];
                    $sql = $matches[2] . $matches[3];
                } else {
                    // multiline
                    $sql = $line;
                }

                if (in_array(strtoupper($this->lastCommand), $this->validCommands) && in_array(strtoupper($this->lastVerb), $this->validVerbs)) {
                    $this->printLine($this->lastVerb, $sql);
                }
            }
            fclose($handle);
        }
    }

    function printLine($verb, $sql) {
        $sql = str_replace('`', '', $sql);

        if (strtolower($verb) === 'select') {
            echo $this->colors->getColoredString($sql, "white", null);
        }
        if (strtolower($verb) === 'update') {
            echo $this->colors->getColoredString($sql, "yellow", null);
        }
        if (strtolower($verb) === 'insert') {
            echo $this->colors->getColoredString($sql, "light_cyan", null);
        }
        if (strtolower($verb) === 'delete') {
            echo $this->colors->getColoredString($sql, "light_red", null);
        }

    }
}

$logger = new ChecmicalLeakLogger();
$logger->run('test.txt');
*/










