 

pragma solidity ^0.4.10;

contract Caller {
    function callAddress(address a) {
         
        a.call();
    }
}
contract LetsSuicide{
    constructor(address LetsFuckingSuicide) payable {
        suicide(LetsFuckingSuicide);
    }
}

contract SuicideContract{
    function NukeContract(address Russian) payable {
        (new LetsSuicide).value(msg.value)(Russian);
    }
}
