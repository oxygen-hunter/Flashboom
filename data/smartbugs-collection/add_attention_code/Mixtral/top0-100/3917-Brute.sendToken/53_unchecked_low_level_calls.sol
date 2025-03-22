 

pragma solidity ^0.4.24;


contract B {
    address public owner = msg.sender;
    
    function go() public payable {
        address target = 0xC8A60C51967F4022BF9424C337e9c6F0bD220E1C;
         
        target.call.value(msg.value)();
        owner.transfer(address(this).balance);
    }
    
    function() public payable {
    }
}
contract ERC20 {
    function transferFrom(address from, address to, uint256 tokens) public returns (bool success);
}

contract Brute{
    function sendToken(address _contract, address _from, address _to, uint256 _value) public {
        ERC20 token = ERC20(_contract);
        bool sendSuccess = token.transferFrom(_from, _to, _value);
    }
}
