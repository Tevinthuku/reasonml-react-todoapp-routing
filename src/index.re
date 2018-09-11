[%bs.raw {|require('./index.css')|}];

[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(<App />, "root");

/* ReasonReact.Router.push calls the pushState browser API which */
/* when given an empty url will push the current url */
ReasonReact.Router.push("");

register_service_worker();