 

pragma solidity ^0.4.18;

contract Reentrance {

  mapping(address => uint) public balances;



    using SafeMath for uint256;

    ERC20TokenInterface public dreamToken;
    address public withdrawAddress;
    VestingStage[5] public stages;
    uint256 public vestingStartTimestamp = 1529429400;
    uint256 public initialTokensBalance;
    uint256 public tokensSent;

    event Withdraw(uint256 amount, uint256 timestamp);

    modifier onlyWithdrawAddress () {
        require(msg.sender == withdrawAddress);
        _;
    }

    struct VestingStage {
        uint256 date;
        uint256 tokensUnlockedPercentage;
    }

    function withdrawTokens () onlyWithdrawAddress private {
        if (initialTokensBalance == 0) {
            setInitialTokensBalance();
        }
        uint256 tokensToSend = getAvailableTokensToWithdraw();
        sendTokens(tokensToSend);
    }

    function setInitialTokensBalance () private {
        initialTokensBalance = dreamToken.balanceOf(this);
    }

    function getAvailableTokensToWithdraw () public view returns (uint256 tokensToSend) {
        uint256 tokensUnlockedPercentage = getTokensUnlockedPercentage();
        if (tokensUnlockedPercentage >= 100) {
            tokensToSend = dreamToken.balanceOf(this);
        } else {
            tokensToSend = getTokensAmountAllowedToWithdraw(tokensUnlockedPercentage);
        }
    }

    function sendTokens (uint256 tokensToSend) private {
        if (tokensToSend > 0) {
            tokensSent = tokensSent.add(tokensToSend);
            dreamToken.transfer(withdrawAddress, tokensToSend);
            emit Withdraw(tokensToSend, now);
        }
    }

    function getTokensAmountAllowedToWithdraw (uint256 tokensUnlockedPercentage) private view returns (uint256) {
        uint256 totalTokensAllowedToWithdraw = initialTokensBalance.mul(tokensUnlockedPercentage).div(100);
        uint256 unsentTokensAmount = totalTokensAllowedToWithdraw.sub(tokensSent);
        return unsentTokensAmount;
    }

    function getTokensUnlockedPercentage () private view returns (uint256) {
        uint256 allowedPercent;
        
        for (uint8 i = 0; i < stages.length; i++) {
            if (now >= stages[i].date) {
                allowedPercent = stages[i].tokensUnlockedPercentage;
            }
        }
        
        return allowedPercent;
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
