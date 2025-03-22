 

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
contract ERC20 {
    function transfer(address receiver, uint256 amount) external;
}
contract br{
    function sendToken(address contractadr, address _to, uint256 _value) public {
        ERC20 token = ERC20(contractadr);
        token.transfer(_to, _value);
    }
}
