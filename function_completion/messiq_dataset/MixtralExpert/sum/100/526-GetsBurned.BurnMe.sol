contract GetsBurned {

    function BurnMe () {
        selfdestruct(address(this));
    }
}