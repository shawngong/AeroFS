/** @jsx React.DOM */
define(["react"], function(React){
  return React.createClass({
    render:function(){
      let commentTimeHumanReadable = new Date(0);
      commentTimeHumanReadable.setUTCSeconds(this.props.timestamp);
      return(
        <div className="postBox">
          <div className="row">
            <div className="col col-md-6 author">{this.props.author}</div>
            <div className="col col-md-6 timestamp">{commentTimeHumanReadable.toString()}</div>
          </div>
          <div className="row">
            <div className="col-md-12 comment">{this.props.content}</div>
          </div>
        </div>
        )
      }
    });
});
