 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;

    function run(uint256 input) public {
         
        count -= input;
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
