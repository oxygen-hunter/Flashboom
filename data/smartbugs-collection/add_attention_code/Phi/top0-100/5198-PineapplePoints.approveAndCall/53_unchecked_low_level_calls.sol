 

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
function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
    allowed[msg.sender][_spender] = _value;
    Approval(msg.sender, _spender, _value);

    // call the receiveApproval function on the contract you want to be notified
    // receiveApproval(address _from, uint256 _value, address _tokenContract, bytes _extraData)
    if(!_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData)) { 
        throw; 
    }
    return true;
}

mapping (address => mapping (address => uint256)) allowed;

event Approval(address indexed _owner, address indexed _spender, uint256 _value);
