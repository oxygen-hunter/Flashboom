 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;



    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        if(!_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData)) { throw; }
        return true;
    }

    string public name;                   
    uint8 public decimals;                
    string public symbol;               
    string public version = 'H1.0';       

    mapping (address => uint256) balances;
    mapping (address => mapping (address => uint256)) allowed;
    uint256 public totalSupply;
    
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);

    function run(uint256 input) public {
         
        count -= input;
    }
}
