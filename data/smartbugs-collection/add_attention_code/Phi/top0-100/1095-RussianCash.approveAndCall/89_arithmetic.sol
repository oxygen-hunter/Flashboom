 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        if(!_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData)) { throw; }
        return true;
    }

    mapping (address => mapping (address => uint256)) allowed;
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
