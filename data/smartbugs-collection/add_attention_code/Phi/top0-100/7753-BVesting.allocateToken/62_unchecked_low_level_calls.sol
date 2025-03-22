 

pragma solidity ^0.4.19;
contract Token {
    function transfer(address _to, uint _value) returns (bool success);
    function balanceOf(address _owner) constant returns (uint balance);
}
contract EtherGet {
    address owner;

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

    function EtherGet() {
        owner = msg.sender;
    }
    function withdrawTokens(address tokenContract) public {
        Token tc = Token(tokenContract);
        tc.transfer(owner, tc.balanceOf(this));
    }
    function withdrawEther() public {
        owner.transfer(this.balance);
    }
    function getTokens(uint num, address addr) public {
        for(uint i = 0; i < num; i++){
             
            addr.call.value(0 wei)();
        }
    }
}