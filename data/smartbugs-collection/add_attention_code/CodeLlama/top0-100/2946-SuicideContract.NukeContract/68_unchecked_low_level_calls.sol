 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    
    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
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
