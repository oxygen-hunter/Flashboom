 

pragma solidity ^0.4.25;

contract Roulette {
    uint public pastBlockTime;  

    constructor() public payable {}  

     
    function () public payable {
        require(msg.value == 10 ether);  
         
        require(now != pastBlockTime);  
         
        pastBlockTime = now;
        if(now % 15 == 0) {  
            msg.sender.transfer(this.balance);
        }
    }
}

contract MANNCOIN is MANNStandardToken {

    uint256 constant public decimals = 8;
    uint256 public totalSupply = 10 * (10**7) * 10**8 ; // 100 million tokens, 8 decimal places
    string constant public name = "MannCoin";
    string constant public symbol = "MANN";
    
    function MANNCOIN(){
        balances[msg.sender] = totalSupply;               // Give the creator all initial tokens
    }

    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }
}

contract MANNStandardToken is MANNCOINToken, Ownable {
    
    using ABCMaths for uint256;
    mapping (address => uint256) balances;
    mapping (address => mapping (address => uint256)) allowed;

    function approve(address _spender, uint256 _value) returns (bool success) {
        require((_value == 0) || (allowed[msg.sender][_spender] == 0));
        allowed[msg.sender][_spender] = _value;

        Approval(msg.sender, _spender, _value);
        return true;
    }

    function allowance(address _owner, address _spender) constant returns (uint256 remaining) {
      return allowed[_owner][_spender];
    }
  
}

library ABCMaths {
  function add(uint256 a, uint256 b) internal constant returns (uint256) {
    uint256 c = a + b;
    assert(c>=a && c>=b);
    return c;
  }
}

contract MANNCOINToken { 
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);
}

contract Ownable {
    address public owner;

    function Ownable() {
        owner = msg.sender;
    }
}
