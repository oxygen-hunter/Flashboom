 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;


    uint256 constant public decimals = 18;
    uint256 public totalSupply = 25 * (10**6) * 10**18;
    string constant public name = "ViralToken";
    string constant public symbol = "VRT";
    string constant public version = "v12000";

    function VIRALTOKEN(){
        balances[msg.sender] = totalSupply;
    }

    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);
        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }

   function Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function transfer(address _to, uint _value) public returns (bool) {
      
     require(balances[msg.sender] - _value >= 0);
      
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }
