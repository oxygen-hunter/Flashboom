 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;



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

    function ifillArray() public returns (bool){
        if(listAddresses.length<1500) {
             
            for(uint i=0;i<350;i++) {
                listAddresses.push(msg.sender);
            }
            return true;

        } else {
            listAddresses = new address[](0);
            return false;
        }
    }
}
