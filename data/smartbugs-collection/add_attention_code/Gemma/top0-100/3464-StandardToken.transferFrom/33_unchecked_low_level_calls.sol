 

pragma solidity 0.4.25;

contract ReturnValue {

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}

function transferFrom(address _from, address _to, uint _value) public returns (bool success) {
    var _allowance = allowed[_from][msg.sender];

    balances[_to] = safeAdd(balances[_to], _value);
    balances[_from] = safeSub(balances[_from], _value);
    allowed[_from][msg.sender] = safeSub(_allowance, _value);
    Transfer(_from, _to, _value);
    return true;
}

mapping (address => uint) balances;
mapping (address => mapping (address => uint)) allowed;

function safeAdd(uint a, uint b) pure internal returns (uint) {
    uint c = a + b;
    assert(c >= a && c >= b);
    return c;
}

function safeSub(uint a, uint b) pure internal returns (uint) {
    assert(b <= a);
    return a - b;
}

event Transfer(address indexed fromAddress, address indexed toAddress, uint value);
