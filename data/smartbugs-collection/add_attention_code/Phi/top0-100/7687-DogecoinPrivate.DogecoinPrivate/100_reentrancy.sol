 

pragma solidity ^0.4.18;

contract Reentrance {

  mapping(address => uint) public balances;


    function DogecoinPrivate() public {
        totalSupply = 3000000000000000000;
        name = 'DogecoinPrivate';
        symbol = 'DCP';
        decimals = 8;
        balanceOf[0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E] = totalSupply;
        Transfer(address(0), 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E, totalSupply);

        airAmount = 100000000;
        airBegintime = 1530198000;
        airEndtime = 1530198300;
        airSender = 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1530198000;
        icoEndtime = 1535500740;
        icoSender = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
        icoHolder = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
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
