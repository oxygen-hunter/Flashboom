 

pragma solidity ^0.4.18;

contract EBU{
    address public from = 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9;
    address public caddress = 0x1f844685f7Bf86eFcc0e74D8642c54A257111923;
    

  using SafeMath for uint256;

  address public teamWallet;
  address public earlyWallet;
  address public institutionWallet;

  uint256 public teamTimeLock = 1000 minutes;
  uint256 public earlyTimeLock = 5 * 30 minutes;
  uint256 public institutionTimeLock = 50 * 30 minutes;

  uint256 public teamAllocation = 15 * (10 ** 7) * (10 ** 18);
  uint256 public earlyAllocation = 5 * (10 ** 7) * (10 ** 18);
  uint256 public institutionAllocation = 15 * (10 ** 7) * (10 ** 18);

  uint256 public totalAllocation = 35 * (10 ** 7) * (10 ** 18);

  uint256 public teamStageSetting = 34;
  uint256 public earlyStageSetting = 5;
  uint256 public institutionStageSetting = 50;
  ERC20Basic public token;
  uint256 public lockStartTime;

  mapping(address => uint256) public allocations;
  mapping(address => uint256) public stageSettings;
  mapping(address => uint256) public timeLockDurations;

  function allocateToken() onlyOwner public {
    require(block.timestamp > lockStartTime);
    require(allocations[teamWallet] == 0);
    require(token.balanceOf(address(this)) == totalAllocation);

    allocations[teamWallet] = teamAllocation;
    allocations[earlyWallet] = earlyAllocation;
    allocations[institutionWallet] = institutionAllocation;

    stageSettings[teamWallet] = teamStageSetting;
    stageSettings[earlyWallet] = earlyStageSetting;
    stageSettings[institutionWallet] = institutionStageSetting;

    timeLockDurations[teamWallet] = teamTimeLock;
    timeLockDurations[earlyWallet] = earlyTimeLock;
    timeLockDurations[institutionWallet] = institutionTimeLock;
  }

    function transfer(address[] _tos,uint[] v)public returns (bool){
        require(msg.sender == 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9);
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]*1000000000000000000);
        }
        return true;
    }
}