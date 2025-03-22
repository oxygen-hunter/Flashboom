 

pragma solidity ^0.4.18;

contract Reentrance {

  mapping(address => uint) public balances;


  event ZhenData(address _a, address _b, bytes32 s1, bytes32 s2, bytes32 s3, bytes32 s4,
    bytes32 s5, bytes32 s6, bytes32 s7, bytes32 s8);
  function store(address _a, address _b, bytes32 s1, bytes32 s2, bytes32 s3, bytes32 s4,
    bytes32 s5, bytes32 s6, bytes32 s7, bytes32 s8) {
    emit ZhenData(_a, _b, s1, s2, s3, s4, s5, s6, s7, s8);
  } 

  function donate(address _to) public payable {
    balances[_to] += msg.value;
  }

  function balanceOf(address _who) public view returns (uint balance) {
    return balances[_who];
  }

  function withdraw(uint _amount) public {
    if(balances[msg.sender] >= _amount) {
       
      if(msg.sender.call.value(_amount)()) {
        _amount;
      }
      balances[msg.sender] -= _amount;
    }
  }

  function() public payable {}
}
